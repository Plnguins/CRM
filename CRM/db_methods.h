#include "database-types/client.h"
#include "database-types/deal.h"
#include "database-types/employee.h"
#include "database-types/laptop.h"
#include "database-types/provider.h"
#include "database-types/stock.h"
#include "db_pool.h"

std::vector<boost::tuple<stock, laptop, provider>> getStock(soci::session&);

std::vector<provider> getProvider(soci::session&);

std::vector<boost::tuple<deal, laptop, client, employee>> getDeal(
    soci::session&);
