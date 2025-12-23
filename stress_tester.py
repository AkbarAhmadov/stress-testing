#!/usr/bin/env python3

# python3 stress_tester.py --max 200000 --timeout 2 --progress 100

# stress_tester.py
# Kullanım örneği:
#   python3 stress_tester.py --max 10000 --timeout 1.5 --progress 200
#
# Gereksinim: correct.cpp, hack.cpp, generator.cpp aynı klasörde olmalı.

import subprocess
import shutil
import argparse
import sys
import os

parser = argparse.ArgumentParser(description='Stress tester: generator -> correct vs hack')
parser.add_argument('--max', type=int, default=1000000, help='Maximum test sayısı')
parser.add_argument('--timeout', type=float, default=2.0, help='Her program için timeout (saniye)')
parser.add_argument('--progress', type=int, default=100, help='Kaç testte bir ilerlemeyi yazsın')
parser.add_argument('--correct-src', type=str, default='correct.cpp', help='Doğru çözüm kaynağı')
parser.add_argument('--hack-src', type=str, default='hack.cpp', help='Test edilecek çözüm kaynağı')
parser.add_argument('--gen-src', type=str, default='generator.cpp', help='Generator kaynağı')
parser.add_argument('--keep-files', action='store_true', help='Fark bulunduğunda temporary dosyaları silme')
args = parser.parse_args()

# Varsayılan ikili adları
CORRECT_BIN = 'correct'
HACK_BIN = 'hack'
GEN_BIN = 'gen'

def die(msg, code=1):
    print(msg)
    sys.exit(code)

def compile_sources():
    if shutil.which('g++') is None:
        die('g++ bulunamadı. Lütfen sistemine g++ kur.')
    sources = [
        (args.correct_src, CORRECT_BIN),
        (args.hack_src, HACK_BIN),
        (args.gen_src, GEN_BIN)
    ]
    for src, out in sources:
        if not os.path.exists(src):
            die(f"Gerekli dosya bulunamadı: {src}")
        cmd = ['g++', '-O2', src, '-std=c++17', '-o', out]
        print('Derleniyor:', ' '.join(cmd))
        p = subprocess.run(cmd, capture_output=True, text=True)
        if p.returncode != 0:
            print('--- Derleme stderr ---')
            print(p.stderr)
            die(f"Derleme hatası: {src}")
        else:
            if p.stderr.strip():
                print('Derleme uyarısı:', p.stderr.strip())

def normalize(s: str) -> str:
    # Fazladan boşlukları tekleştir, satır sonlarını tek tip yap
    if s is None:
        return ''
    return ' '.join(s.strip().split())

def run_bin(path, inp, timeout):
    try:
        p = subprocess.run(['./' + path], input=inp, text=True, capture_output=True, timeout=timeout)
        return p.returncode, p.stdout, p.stderr
    except subprocess.TimeoutExpired:
        return None, None, 'TIMEOUT'

def save_debug(inp, out_correct, out_hack, err_correct, err_hack, prefix='found'):
    open(prefix + '_input.txt','w').write(inp or '')
    open(prefix + '_correct_output.txt','w').write(out_correct or '')
    open(prefix + '_hack_output.txt','w').write(out_hack or '')
    open(prefix + '_correct_stderr.txt','w').write(err_correct or '')
    open(prefix + '_hack_stderr.txt','w').write(err_hack or '')
    print(f'Girdi ve çıktılar kaydedildi: {prefix}_*.txt')

def main():
    compile_sources()

    i = 0
    while i < args.max:
        i += 1

        # generator'i çalıştır (stdin yok)
        ret_gen, out_gen, err_gen = run_bin(GEN_BIN, '', args.timeout)
        if ret_gen is None:
            print(f'Generator timeout! Test #: {i}')
            save_debug('', '', '', '', 'GEN_TIMEOUT', prefix='gen_timeout')
            sys.exit(0)
        if ret_gen != 0:
            print(f'Generator non-zero exit ({ret_gen}). stderr:')
            print(err_gen or '<empty>')
            save_debug('', '', '', '', err_gen or '', prefix='gen_error')
            sys.exit(0)

        inp = out_gen

        # correct
        rc1, out1, err1 = run_bin(CORRECT_BIN, inp, args.timeout)
        # hack
        rc2, out2, err2 = run_bin(HACK_BIN, inp, args.timeout)

        # Timeout kontrolü
        if rc1 is None or rc2 is None:
            print(f"Timeout bulundu. Test #: {i}")
            save_debug(inp, out1 or '', out2 or '', err1 or '', err2 or '', prefix='timeout')
            sys.exit(0)

        # Eğer process non-zero döndüyse bunu da loglayalım (crash, runtime error)
        if rc1 != 0 or rc2 != 0:
            print(f'Non-zero exit kodu bulunmuş. Test #: {i}')
            print(f'correct exit: {rc1}, hack exit: {rc2}')
            save_debug(inp, out1 or '', out2 or '', err1 or '', err2 or '', prefix='runtime_error')
            sys.exit(0)

        n1 = normalize(out1)
        n2 = normalize(out2)

        if n1 != n2:
            print('FARK bulundu! Test #:', i)
            print('Özet (doğru vs hack):')
            print('--- correct (ilk 1000 char) ---')
            print((out1 or '')[:1000])
            print('--- hack (ilk 1000 char) ---')
            print((out2 or '')[:1000])
            save_debug(inp, out1 or '', out2 or '', err1 or '', err2 or '', prefix='found')
            if not args.keep_files:
                # opsiyonel: ikilileri silme davranışı istenirse eklenebilir; şimdilik dosyaları bırakıyoruz
                pass
            sys.exit(0)

        if i % args.progress == 0:
            print(f'{i} test çalıştırıldı — hepsi eşit.')

    print('Tüm testler tamamlandı, fark bulunamadı.')

if __name__ == '__main__':
    main()
