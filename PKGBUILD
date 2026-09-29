pkgname=isac
pkgver=0.1.0
pkgrel=1
pkgdesc="Flag parser"
arch=('x86_64')
license=('MIT')
depends=('glibc')
makedepends=('clang' 'make' 'git')

source=("https://github.com/Helix-ISA/isac/archive/refs/heads/master.tar.gz")
sha256sums=('SKIP')

build() {
    cd "$srcdir/isac-master"
    make
}

package() {
    cd "$srcdir/isac-master"

    install -Dm755 bin/isac.so \
        "$pkgdir/usr/lib/isac.so"

    install -Dm644 include/operand.h \
        "$pkgdir/usr/include/isac/operand.h"

    install -Dm644 include/mnemonic.h \
        "$pkgdir/usr/include/isac/mnemonic.h"

    install -Dm644 include/instruction.h \
        "$pkgdir/usr/include/isac/instruction.h"

    install -Dm644 include/format.h \
        "$pkgdir/usr/include/isac/format.h"

    install -Dm644 include/types.h \
        "$pkgdir/usr/include/isac/types.h"
}
