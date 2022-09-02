#include "database-types/advertisement.h"
#include "database-types/client.h"
#include "database-types/deal.h"
#include "database-types/employee.h"
#include "database-types/laptop.h"
#include "database-types/provider.h"
#include "database-types/stock.h"
#include "db_pool.h"

std::vector<boost::tuple<stock, laptop, provider>> getStock(soci::session&,
                                                            const int&,
                                                            const int&);

std::vector<provider> getProvider(soci::session&, const int&, const int&);

std::vector<boost::tuple<deal, laptop, client, employee>> getDeal(
    soci::session&, const int&, const int&);

std::vector<employee> getEmployee(soci::session&, const int&, const int&);

std::vector<advertisement> getAdvertisement(soci::session&, const int&,
                                            const int&);
