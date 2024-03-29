// Database pool for CRM application
// Copyright(C) 2022  Plnguins

// This program is free software : you can redistribute it and / or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.If not, see < https:  // www.gnu.org/licenses/>.
#pragma once
#include <soci/boost-gregorian-date.h>
#include <soci/boost-optional.h>
#include <soci/boost-tuple.h>
#include <soci/connection-pool.h>
#include <soci/postgresql/soci-postgresql.h>
#include <soci/soci.h>

#include <boost/smart_ptr.hpp>  // Умные указатели
#include <boost/smart_ptr.hpp>

class db_pool {
    boost::shared_ptr<soci::connection_pool> pool_;
    std::size_t pool_size_;

   public:
    db_pool() : pool_(nullptr), pool_size_(0) {}
    ~db_pool() { close(); }

    boost::weak_ptr<soci::connection_pool> get_pool() { return pool_; }

    bool connect(const std::string& conn_str, std::size_t pool_size = 5) {
        if (pool_ != nullptr) {
            close();
        }
        pool_size_ = pool_size;
        boost::optional<int> is_connected;
        pool_ = boost::shared_ptr<soci::connection_pool>(
            new soci::connection_pool(pool_size_));
        if (!pool_) {
            return false;
        }
        try {
            for (std::size_t _i = 0; _i < pool_size_; _i++) {
                soci::session& sql = pool_->at(_i);
                sql.open(conn_str);
                sql << "SELECT 1;", soci::into(is_connected);
                if (!is_connected) {
                    break;
                } else if (_i + 1 < pool_size_) {
                    is_connected.get() = 0;
                }
            }
        } catch (std::exception const& e) {
            // Logging
        }
        if (!is_connected) {
            close();
        }
        return (pool_ != nullptr);
    }

    void close() {
        if (pool_ != nullptr) {
            try {
                for (std::size_t _i = 0; _i < pool_size_; _i++) {
                    soci::session& sql = pool_->at(_i);
                    sql.close();
                }
                pool_.reset();
            } catch (std::exception const& e) {
                // Logging
            }
            pool_size_ = 0;
        }
    }
};
