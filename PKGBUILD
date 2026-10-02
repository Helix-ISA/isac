pkgname=isac
pkgver=0.1.0
pkgrel=13
pkgdesc="ISA C headers"
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
        "$pkgdir/usr/lib/libisac.so"

    install -Dm644 include/isac/operand.h \
        "$pkgdir/usr/include/isac/operand.h"

    install -Dm644 include/isac/mnemonic.h \
        "$pkgdir/usr/include/isac/mnemonic.h"

    install -Dm644 include/isac/instruction.h \
        "$pkgdir/usr/include/isac/instruction.h"

    install -Dm644 include/isac/format.h \
        "$pkgdir/usr/include/isac/format.h"

    install -Dm644 include/isac/types.h \
        "$pkgdir/usr/include/isac/types.h"
}
