/*
 * Copyright 2008-2009 Sun Microsystems, Inc.  All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
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

/* @test
 * @bug 6808647
 * @summary Checks that a DirectoryStream's iterator returns the expected
 *    path when opening a directory by specifying only the drive letter.
 * @library ..
 */

import java.nio.file.*;
import java.io.File;
import java.io.IOException;

public class DriveLetter {

    public static void main(String[] args) throws IOException {
        String os = System.getProperty("os.name");
        if (!os.startsWith("Windows")) {
            System.out.println("This is Windows specific test");
            return;
        }
        String here = System.getProperty("user.dir");
        if (here.length() < 2 || here.charAt(1) != ':')
            throw new RuntimeException("Unable to determine drive letter");

        // create temporary file in current directory
        File tempFile = File.createTempFile("foo", "tmp", new File(here));
        try {
            // we should expect C:foo.tmp to be returned by iterator
            String drive = here.substring(0, 2);
            Path expected = Paths.get(drive).resolve(tempFile.getName());

            boolean found = false;
            DirectoryStream<Path> stream = Paths.get(drive).newDirectoryStream();
            try {
                for (Path file : stream) {
                    if (file.equals(expected)) {
                        found = true;
                        break;
                    }
                }
            } finally {
                stream.close();
            }
            if (!found)
                throw new RuntimeException("Temporary file not found???");

        } finally {
            tempFile.delete();
        }
    }
}
