#include <acquisition/utils/utils.h>

namespace utils {

    QByteArray replace_obsolete_timezones(const QByteArray& date)
    {
        // Qt 6.5.3 does not properly parse the non-numeric time-zones that are 
        // declated as obsolete but still allowed in RFC2822.
        constexpr std::array obsolete_timezones = {
            std::make_pair("GMT", "+0000"),
            std::make_pair("UT" , "+0000"),
            std::make_pair("EST", "-0005"),
            std::make_pair("EDT", "-0004"),
            std::make_pair("CST", "-0006"),
            std::make_pair("CDT", "-0005"),
            std::make_pair("MST", "-0007"),
            std::make_pair("MDT", "-0006"),
            std::make_pair("PST", "-0008"),
            std::make_pair("PDT", "-0007") };
        QByteArray fixed = date.trimmed();
        for (const auto& pair : obsolete_timezones) {
            const char* zone = pair.first;
            const char* offset = pair.second;
            if (fixed.endsWith(zone)) {
                fixed = date.chopped(std::strlen(zone)) + offset;
                return fixed;
            };
        };
        return fixed;
    }

    std::string replace_obsolete_timezones(const std::string& date)
    {
        return utils::replace_obsolete_timezones(QByteArray::fromStdString(date)).toStdString();
    }

    QDateTime parseRFC2822(const QByteArray& date)
    {
        const QByteArray fixed_date = replace_obsolete_timezones(date);
        return QDateTime::fromString(fixed_date, Qt::RFC2822Date);
    }

    QDateTime parseRFC2822(const std::string& date)
    {
        return parseRFC2822(QByteArray::fromStdString(date));
    }

    QsLogging::Level loggingLevel(const QString& value)
    {
        const QString v = value.toUpper();
        for (const auto& pair : logging_level_names) {
            if (0 == v.compare(pair.second, Qt::CaseInsensitive)) {
                return pair.first;
            };
        };
        QLOG_ERROR() << "Utils: invalid logging level:" << value;
        return QsLogging::InfoLevel;
    }

    QString loggingLevelName(QsLogging::Level level)
    {
        for (const auto& pair : logging_level_names) {
            if (level == pair.first) {
                return pair.second;
            };
        };
        QLOG_ERROR() << "Utils: invalid logging level:" << level;
        return "<INVALID>";
    }

    QString leaguePrettyName(const QString& league_id)
    {
        return league_id;
    }

}
