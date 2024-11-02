#include <acquisition/search_filters/required_level.h>

RequiredLevelFilter::RequiredLevelFilter(ProxyModel& proxy_model)
    : MinMaxFilter<int>("LVL", proxy_model, &RequiredLevelFilter::requiredLevel)
{
}
