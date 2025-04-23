#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/supplier/supplier.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for supplier table
struct SupplierDTO {
    id_type id = 0;
std::string supplier_id = "";
std::string supplier_name = "";
std::string contact_person = "";
std::string phone = "";
std::string address = "";
std::string rating_level = "";

    // JSON serialization/deserialization
    static SupplierDTO from_json(const nlohmann::json& j) {
        try {
            return SupplierDTO{
                .supplier_id = j.at("supplier_id"),
.supplier_name = j.at("supplier_name"),
.contact_person = j.at("contact_person"),
.phone = j.at("phone"),
.address = j.at("address"),
.rating_level = j.at("rating_level"),
            };
        } catch (const std::exception& e) {
            std::cerr << "[from_json error] " << e.what() << "\n"
                      << "Input JSON: " << j.dump(2) << std::endl;
            throw;
        }
    }
    
    nlohmann::json to_json() const {
        return {
            {"id", id},
{"supplier_id", supplier_id},
{"supplier_name", supplier_name},
{"contact_person", contact_person},
{"phone", phone},
{"address", address},
{"rating_level", rating_level}
        };
    }
};

// ORM mapping
namespace model {
template <>
struct ReflectTable<SupplierDTO, db::supplier> {
    static constexpr auto map_members = std::make_tuple(
        std::make_pair(&SupplierDTO::id, &db::supplier::id),
std::make_pair(&SupplierDTO::supplier_id, &db::supplier::supplier_id),
std::make_pair(&SupplierDTO::supplier_name, &db::supplier::supplier_name),
std::make_pair(&SupplierDTO::contact_person, &db::supplier::contact_person),
std::make_pair(&SupplierDTO::phone, &db::supplier::phone),
std::make_pair(&SupplierDTO::address, &db::supplier::address),
std::make_pair(&SupplierDTO::rating_level, &db::supplier::rating_level)
    );
};

// mapping
template <typename SupplierRow> struct ReflectTableRow<SupplierDTO, SupplierRow> {
    static SupplierDTO assign_model(SupplierRow &&row) {
        return SupplierDTO {
            .id = row.id,
.supplier_id = row.supplier_id,
.supplier_name = row.supplier_name,
.contact_person = row.contact_person,
.phone = row.phone,
.address = row.address,
.rating_level = row.rating_level
        };           
    }
};
} // namespace model
