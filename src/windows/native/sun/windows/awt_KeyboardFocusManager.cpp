/*
 * Copyright 2000-2009 Sun Microsystems, Inc.  All Rights Reserved.
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

#include "awt.h"
#include "awt_Component.h"
#include "awt_Toolkit.h"
#include <java_awt_KeyboardFocusManager.h>
#include <jni.h>

static jobject getNativeFocusState(JNIEnv *env, void*(*ftn)()) {
    jobject gFocusState = (jobject)AwtToolkit::GetInstance().SyncCall(ftn);

    if (gFocusState != NULL) {
        jobject lFocusState = env->NewLocalRef(gFocusState);
        env->DeleteGlobalRef(gFocusState);
        return lFocusState;
    }
    return NULL;
}

extern "C" {

/*
 * Class:     java_awt_KeyboardFocusManager
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_java_awt_KeyboardFocusManager_initIDs
    (JNIEnv *env, jclass cls)
{
}

/*
 * Class:     sun_awt_windows_WKeyboardFocusManagerPeer
 * Method:    setNativeFocusOwner
 * Signature: (Lsun/awt/windows/WComponentPeer)
 */
JNIEXPORT void JNICALL
Java_sun_awt_windows_WKeyboardFocusManagerPeer_setNativeFocusOwner
    (JNIEnv *env, jclass cls, jobject compPeer)
{
    TRY;

    jobject peerGlobalRef = env->NewGlobalRef(compPeer);

    AwtToolkit::GetInstance().SyncCall(AwtComponent::SetNativeFocusOwner,
                                       (void*)peerGlobalRef);
    // peerGlobalRef is deleted in SetNativeFocusOwner

    CATCH_BAD_ALLOC;
}

/*
 * Class:     sun_awt_windows_WKeyboardFocusManagerPeer
 * Method:    getNativeFocusOwner
 * Signature: (Lsun/awt/windows/WComponentPeer)
 */
JNIEXPORT jobject JNICALL
Java_sun_awt_windows_WKeyboardFocusManagerPeer_getNativeFocusOwner
    (JNIEnv *env, jclass cls)
{
    TRY;

    return getNativeFocusState(env, AwtComponent::GetNativeFocusOwner);

    CATCH_BAD_ALLOC_RET(NULL);
}

/*
 * Class:     sun_awt_windows_WKeyboardFocusManagerPeer
 * Method:    getNativeFocusedWindow
 * Signature: ()Ljava/awt/Window;
 */
JNIEXPORT jobject JNICALL
Java_sun_awt_windows_WKeyboardFocusManagerPeer_getNativeFocusedWindow
    (JNIEnv *env, jclass cls)
{
    TRY;

    return getNativeFocusState(env, AwtComponent::GetNativeFocusedWindow);

    CATCH_BAD_ALLOC_RET(NULL);
}
}
