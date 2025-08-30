set -e

OUTDIR=out
export CXX=clang
export CC=clang

mkdir -p $OUTDIR
cd $OUTDIR
cmake ..
make


cd ..
