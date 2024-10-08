/* 
    This file is part of tgl-library

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

    Copyright Ben Wiederhake 2015
*/

#include "config.h"

#ifndef TGL_AVOID_OPENSSL

#include <openssl/err.h>

#include "err.h"

void TGLC_err_print_errors_fp (FILE *fp) {
  ERR_print_errors_fp (fp);
}

int TGLC_init (struct tgl_state *TLS) {
  // Doesn't seem to need any initialization.
  // vlogprintf (6, "Init OpenSSL (no-op)\n");
  return 0;
}

#endif
