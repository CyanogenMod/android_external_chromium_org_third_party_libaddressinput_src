// Copyright (C) 2013 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef I18N_ADDRESSINPUT_LOCALIZATION_H_
#define I18N_ADDRESSINPUT_LOCALIZATION_H_

#include <libaddressinput/address_field.h>
#include <libaddressinput/address_problem.h>

#include <string>
#include <vector>

namespace i18n {
namespace addressinput {

struct AddressData;

// The object to retrieve localized strings based on message IDs. Sample usage:
//    Localization localization;
//    localization.SetLanguage("en");
//    std::string best_language_tag;
//    Process(BuildComponents("CA", localization, &best_language_tag));
//
// Alternative usage:
//    Localization localization;
//    localization.SetGetter(&MyStringGetter, "fr");
//    std::string best_language_tag;
//    Process(BuildComponents("CA", localization, &best_language_tag));
class Localization {
 public:
  // Initializes with English messages by default.
  Localization();
  ~Localization();

  // Returns the localized string for |message_id|. Returns an empty string if
  // there's no message with this identifier.
  std::string GetString(int message_id) const;

  // Returns the error message. If |enable_examples| is false, then the error
  // message will not contain examples of valid input. If |enable_links| is
  // false, then the error message will not contain HTML links. (Some error
  // messages contain postal code examples or link to post office websites to
  // look up the postal code for an address). Vector field values (e.g. for
  // street address) should not be empty if problem is UNKNOWN_VALUE. The
  // POSTAL_CODE field should only be used with MISSING_REQUIRED_FIELD,
  // INVALID_FORMAT, and MISMATCHING_VALUE problem codes. All other fields
  // should only be used with MISSING_REQUIRED_FIELD, UNKNOWN_VALUE, and
  // USES_P_O_BOX problem codes.
  std::string GetErrorMessage(const AddressData& address,
                              AddressField field,
                              AddressProblem problem,
                              bool enable_examples,
                              bool enable_links);

  // Sets the language for the strings. The only supported language is "en"
  // until we have translations.
  void SetLanguage(const std::string& language_tag);

  // Sets the string getter that takes a message identifier and returns the
  // corresponding localized string. The |language_tag| parameter is used only
  // for information purposes here.
  void SetGetter(std::string (*getter)(int), const std::string& language_tag);

  // Returns the current language tag.
  const std::string& GetLanguage() const { return language_tag_; }

 private:
  // Returns the error message where the address field is a postal code. Helper
  // to |GetErrorMessage|. If |postal_code_example| is empty, then the error
  // message will not contain examples of valid postal codes. If
  // |post_service_url| is empty, then the error message will not contain a post
  // service URL. The problem should only be one of MISSING_REQUIRED_FIELD,
  // INVALID_FORMAT, or MISMATCHING_VALUE.
  std::string GetErrorMessageForPostalCode(const AddressData& address,
                                           AddressProblem problem,
                                           bool uses_postal_code_as_label,
                                           std::string postal_code_example,
                                           std::string post_service_url);

  // Calls |parameters.push_back| with 2 strings: the opening and closing tags
  // of the given URL's HTML link.
  void PushBackUrl(std::vector<std::string>& parameters, const std::string url);

  // The string getter.
  std::string (*get_string_)(int);

  // The current language tag.
  std::string language_tag_;
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_LOCALIZATION_H_
