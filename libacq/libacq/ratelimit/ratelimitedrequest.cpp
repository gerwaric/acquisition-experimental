#include <libacq/ratelimit/ratelimitedrequest.h>

// Total number of rate-limited requests that have been created.
unsigned long RateLimitedRequest::request_count = 0;