#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/supplier/supplier.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for myvenv table
struct SupplierDTO {
  inline static const std::vector<std::string> required_fields = {
    "supplier_id", "supplier_name", "contact_person", "contact_phone",
    "email",       "create_at",     "status",         "remark"};

  inline static const std::vector<std::string> status_domain = {
    "normal", "inactive", "blacklisted"};


  in_id_type id = 0;
  std::string supplier_id = "";
  std::string supplier_name = "";
  std::string contact_person = "";
  std::string contact_phone = "";
  std::string email = "";
  datetime_type created_at = {};
  std::string status = "";
  std::string remark = "";

  // JSON serialization/deserialization
  static SupplierDTO from_json(const nlohmann::json& j)
  {
    try {
      return SupplierDTO{
        .supplier_id = j.at("supplier_id").get<std::string>(),
        .supplier_name = j.at("supplier_name").get<std::string>(),
        .contact_person = j.at("contact_person").get<std::string>(),
        .contact_phone = j.at("contact_phone").get<std::string>(),
        .email = j.at("email").get<std::string>(),
        .created_at =
          utils::string_to_time(j.at("created_at").get<std::string>()),
        .status = j.at("status").get<std::string>(),
        .remark = j.at("remark").get<std::string>(),
      };
    }
    catch (const std::exception& e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json& j, const SupplierDTO& supplier_dto)
{
  j = nlohmann::json{
    {"id", supplier_dto.id},
    {"supplier_id", supplier_dto.supplier_id},
    {"supplier_name", supplier_dto.supplier_name},
    {"contact_person", supplier_dto.contact_person},
    {"contact_phone", supplier_dto.contact_phone},
    {"email", supplier_dto.email},
    {"created_at", utils::datetime_to_string(supplier_dto.created_at)},
    {"status", supplier_dto.status},
    {"remark", supplier_dto.remark}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<SupplierDTO, db::supplier> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&SupplierDTO::id, &db::supplier::id),
    std::make_pair(&SupplierDTO::supplier_id, &db::supplier::supplier_id),
    std::make_pair(&SupplierDTO::supplier_name, &db::supplier::supplier_name),
    std::make_pair(&SupplierDTO::contact_person, &db::supplier::contact_person),
    std::make_pair(&SupplierDTO::contact_phone, &db::supplier::contact_phone),
    std::make_pair(&SupplierDTO::email, &db::supplier::email),
    std::make_pair(&SupplierDTO::created_at, &db::supplier::created_at),
    std::make_pair(&SupplierDTO::status, &db::supplier::status),
    std::make_pair(&SupplierDTO::remark, &db::supplier::remark));
};

// mapping
template <typename SupplierRow>
struct ReflectTableRow<SupplierDTO, SupplierRow> {
  static SupplierDTO assign_model(SupplierRow&& row)
  {
    return SupplierDTO{.id = row.id,
                       .supplier_id = row.supplier_id,
                       .supplier_name = row.supplier_name,
                       .contact_person = row.contact_person,
                       .contact_phone = row.contact_phone,
                       .email = row.email,
                       .created_at = row.created_at,
                       .status = row.status,
                       .remark = row.remark};
  }
};
}  // namespace model
