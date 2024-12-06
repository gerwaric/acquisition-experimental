#pragma once

#include <json_struct/json_struct.h>
#include <QsLog/QsLog.h>

#include <QByteArray>
#include <QDateTime>
#include <QMetaEnum>

#include <string>
#include <string_view>

namespace utils {

    template<typename Struct>
    std::unique_ptr<Struct> parse_json(const QByteArray& bytes)
    {
        auto payload = std::make_unique<Struct>();
        JS::ParseContext parseContext(bytes);
        if (parseContext.parseTo(payload) != JS::Error::NoError) {
            QLOG_ERROR() << "Error parsing JSON to" << typeid(Struct).name() << ":" << parseContext.makeErrorString();
        };
        return std::move(payload);
    };

    constexpr std::array logging_level_names = {
        std::make_pair(QsLogging::TraceLevel, "Trace"),
        std::make_pair(QsLogging::DebugLevel, "Debug"),
        std::make_pair(QsLogging::InfoLevel,  "Info"),
        std::make_pair(QsLogging::WarnLevel,  "Warn"),
        std::make_pair(QsLogging::ErrorLevel, "Error"),
        std::make_pair(QsLogging::FatalLevel, "Fatal"),
        std::make_pair(QsLogging::OffLevel,   "Off")
    };

    inline bool ends_with(std::string_view str, std::string_view suffix)
    {
        return (str.size() >= suffix.size())
            && (str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0);
    };

    inline bool starts_with(std::string_view str, std::string_view prefix)
    {
        return (str.size() >= prefix.size())
            && (str.compare(0, prefix.size(), prefix) == 0);
    };

    QByteArray replace_obsolete_timezones(const QByteArray& rfc2822_date);

    std::string replace_obsolete_timezones(const std::string& date);

    QDateTime parseRFC2822(const QByteArray& rfc2822_date);

    QDateTime parseRFC2822(const std::string& rfc2822_date);

    QsLogging::Level loggingLevel(const QString& value);

    QString loggingLevelName(QsLogging::Level level);

    template<typename QEnum>
    QString QtEnumToString(const QEnum value)
    {
        return QMetaEnum::fromType<QEnum>().valueToKey(static_cast<int>(value));    
    }

    template<typename QEnum>
    QEnum QtStringtoEnum(const QString& key)
    {
        bool ok = false;
        int value = QMetaEnum::fromType<QEnum>().keyToValue(key.toUtf8().constData(), &ok);
        if (!ok) {
            QLOG_ERROR() << "Error converting string to" << typeid(QEnum).name() << ":" << key;
        };
        return static_cast<QEnum>(value);
    }

    QString leaguePrettyName(const QString& league_id);
}
