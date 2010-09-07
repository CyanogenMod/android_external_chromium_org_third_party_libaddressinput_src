/*
 * Copyright (C) 2010 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.i18n.addressinput;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Utility functions used by the address widget.
 */
public class Util {
  // In upper-case, since we convert the language code to upper case before doing string comparison.
  private static final String LATIN_SCRIPT = "LATN";

  // Cannot instantiate this class - private constructor.
  private Util() {}

  /**
   * Returns true if the language code is explicitly marked to be in the latin script. For example,
   * "zh-Latn" would return true, but "zh-TW", "en" and "zh" would all return false.
   */
  public static boolean isExplicitLatinScript(String languageCode) {
    // Convert to upper-case for easier comparison.
    languageCode = languageCode.toUpperCase();
    // Check to see if the language code contains a script modifier.
    final Pattern languageCodePattern = Pattern.compile("\\w{2}[-_](\\w{4})");
    Matcher m = languageCodePattern.matcher(languageCode);
    if (m.lookingAt()) {
      String script = m.group(1);
      if (script.equals(LATIN_SCRIPT)) {
        return true;
      }
    }
    return false;
  }

  /**
   * Trims the string. If the field is empty after trimming, returns null instead. Note that this
   * only trims ASCII white-space.
   */
  public static String trimToNull(String originalStr) {
    if (originalStr == null) {
      return null;
    }
    String trimmedString = originalStr.trim();
    return (trimmedString.length() == 0) ? null : trimmedString;
  }
}
