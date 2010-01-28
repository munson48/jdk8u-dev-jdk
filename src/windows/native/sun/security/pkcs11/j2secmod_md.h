/*
 * Copyright 2005 Sun Microsystems, Inc.  All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Sun designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Sun in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
 * CA 95054 USA or visit www.sun.com if you need additional information or
 * have any questions.
 */

#include <windows.h>

// in nss.h:
// extern PRBool NSS_VersionCheck(const char *importedVersion);
// extern SECStatus NSS_Init(const char *configdir);
typedef int __declspec(dllimport) (*FPTR_VersionCheck)(const char *importedVersion);
typedef int __declspec(dllimport) (*FPTR_Init)(const char *configdir);

// in secmod.h
//extern SECMODModule *SECMOD_LoadModule(char *moduleSpec,SECMODModule *parent,
//                                                      PRBool recurse);
//char **SECMOD_GetModuleSpecList(SECMODModule *module);
//extern SECMODModuleList *SECMOD_GetDBModuleList(void);

typedef void __declspec(dllimport) *(*FPTR_LoadModule)(char *moduleSpec, void *parent, int recurse);
typedef char __declspec(dllimport) **(*FPTR_GetModuleSpecList)(void *module);
typedef void __declspec(dllimport) *(*FPTR_GetDBModuleList)(void);
