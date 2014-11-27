/* Twofold-Qt
 * (C) Copyright 2014 HicknHack Software GmbH
 *
 * The original code can be found at:
 *     https://github.com/hicknhack-software/Twofold-Qt
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "Call.h"

#include "Twofold/intern/PreparedJavascriptBuilder.h"
#include "Twofold/intern/LineProcessor.h"

#include "Twofold/intern/QStringHelper.h"
#include "Twofold/intern/QCharHelper.h"

namespace Twofold {
namespace intern {
namespace Line {

Call::Call(PreparedJavascriptBuilder &builder)
    : m_builder(builder)
{
}

void Call::operator()(const FileLine &line) const
{
    auto begin = line.firstNonSpace+1;
    auto end = std::find_if_not(begin, line.end, QCharHelper::isSpace);

    m_builder << PushTargetIndentation {{line, TextSpan {begin, end}}};
    m_builder << OriginScript {{line, TextSpan {end, line.end}}};
    m_builder << PopTargetIndentation{{line, TextSpan {line.end, line.end}}};
}

} // namespace Line
} // namespace intern
} // namespace Twofold
