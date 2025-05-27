#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/supplier/supplier_contract.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for supplier_contract table
struct SupplierContractDTO {
  inline static const std::vector<std::string> required_fields = {
    "contract_id",    "supplier_id", "start_date", "end_date",
    "contract_amount", "status",     "file_path"};

  inline static const std::vector<std::string> status_domain = {"active", "expired",
                                                          "terminated"};

  in_id_type id = 0;
  std::string contract_id = "";
  in_id_type supplier_rk_id = 0;
  datetime_type start_date = {};
  datetime_type end_date = {};
  double contract_amount = 0.0;
  std::string status = "";
  std::string file_path = "";

  // JSON serialization/deserialization
  static SupplierContractDTO from_json(const nlohmann::json& j)
  {
    try {
            return SupplierContractDTO{
                .contract_id = j.at("contract_id").get<std::string>(),
                .supplier_rk_id = getInternalId("supplier",j.at("supplier_id").get<ex_id_type>(),
                .start_date = utils::string_to_datetime(j.at("start_date").get<std::string>()),
                .end_date = utils::string_to_datetime(j.at("end_date").get<std::string>()),
                .contract_amount = j.at("contract_amount").get<double>(),
                .status = j.at("status").get<std::string>(),
                .file_path = j.at("file_path").get<std::string>(),
            };
    }
    catch (const std::exception& e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json& j,
                    const SupplierContractDTO& supplier_contract_dto)
{
  j = nlohmann::json{
    {"id", supplier_contract_dto.id},
    {"contract_id", supplier_contract_dto.contract_id},
    {"supplier_id", SupplierContractDTO::getExternalId(
                      "supplier", supplier_contract_dto.supplier_rk_id)},
    {"start_date", utils::datetime_to_string(supplier_contract_dto.start_date)},
    {"end_date", utils::datetime_to_string(supplier_contract_dto.end_date)},
    {"contract_amount", supplier_contract_dto.contract_amount},
    {"status", supplier_contract_dto.status},
    {"file_path", supplier_contract_dto.file_path}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<SupplierContractDTO, db::supplier_contract> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&SupplierContractDTO::id, &db::supplier_contract::id),
    std::make_pair(&SupplierContractDTO::contract_id,
                   &db::supplier_contract::contract_id),
    std::make_pair(&SupplierContractDTO::supplier_rk_id,
                   &db::supplier_contract::supplier_rk_id),
    std::make_pair(&SupplierContractDTO::start_date,
                   &db::supplier_contract::start_date),
    std::make_pair(&SupplierContractDTO::end_date,
                   &db::supplier_contract::end_date),
    std::make_pair(&SupplierContractDTO::contract_amount,
                   &db::supplier_contract::contract_amount),
    std::make_pair(&SupplierContractDTO::status,
                   &db::supplier_contract::status),
    std::make_pair(&SupplierContractDTO::file_path,
                   &db::supplier_contract::file_path));
};

// mapping
template <typename Supplier_contractRow>
struct ReflectTableRow<SupplierContractDTO, Supplier_contractRow> {
  static SupplierContractDTO assign_model(Supplier_contractRow&& row)
  {
    return SupplierContractDTO{.id = row.id,
                               .contract_id = row.contract_id,
                               .supplier_rk_id = row.supplier_rk_id,
                               .start_date = row.start_date,
                               .end_date = row.end_date,
                               .contract_amount = row.contract_amount,
                               .status = row.status,
                               .file_path = row.file_path};
  }
};
}  // namespace model
