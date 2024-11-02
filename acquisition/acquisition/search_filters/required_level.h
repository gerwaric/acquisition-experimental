#pragma once

#include <acquisition/search_filters/min_max_filter.h>

class RequiredLevelFilter : public MinMaxFilter<int>
{
public:
    RequiredLevelFilter(ProxyModel& proxy_model);
private:
    static inline int requiredLevel(const ItemInfo& info) {
        return info.required_level;
    }
};
