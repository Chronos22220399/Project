#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/supplier/supplier_evaluation.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for supplier_evaluation table
struct SupplierEvaluationDTO : CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "evaluation_id",     //
    "supplier_id",       //
    "evaluation_date",   //
    "service_score",     //
    "qualify_score",     //
    "timeliness_score",  //
    "total_score",       //
    "comment",           //
    "remark"             //
  };

  in_id_type id = 0;
  std::string evaluation_id = "";
  in_id_type supplier_rk_id = 0;
  datetime_type evaluation_date = {};
  double service_score = 0.0;
  double qualify_score = 0.0;
  double timeliness_score = 0.0;
  double total_score = 0.0;
  std::string comment = "";
  std::string remark = "";

  // JSON serialization/deserialization
  static SupplierEvaluationDTO from_json(const nlohmann::json& j)
  {
    try {
      return SupplierEvaluationDTO{
        .evaluation_id = j.at("evaluation_id").get<std::string>(),
        .supplier_rk_id =
          getInternalId("supplier", j.at("supplier_id").get<ex_id_type>()),
        .evaluation_date =
          utils::string_to_datetime(j.at("evaluation_date").get<std::string>()),
        .service_score = j.at("service_score").get<double>(),
        .qualify_score = j.at("qualify_score").get<double>(),
        .timeliness_score = j.at("timeliness_score").get<double>(),
        .total_score = j.at("total_score").get<double>(),
        .comment = j.at("comment").get<std::string>(),
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

inline void to_json(nlohmann::json& j,
                    const SupplierEvaluationDTO& supplier_evaluation_dto)
{
  j = nlohmann::json{
    {"id", supplier_evaluation_dto.id},
    {"evaluation_id", supplier_evaluation_dto.evaluation_id},
    {"supplier_id", SupplierEvaluationDTO::getExternalId(
                      "supplier", supplier_evaluation_dto.supplier_rk_id)},
    {"evaluation_date",
     utils::datetime_to_string(supplier_evaluation_dto.evaluation_date)},
    {"service_score", supplier_evaluation_dto.service_score},
    {"qualify_score", supplier_evaluation_dto.qualify_score},
    {"timeliness_score", supplier_evaluation_dto.timeliness_score},
    {"total_score", supplier_evaluation_dto.total_score},
    {"comment", supplier_evaluation_dto.comment},
    {"remark", supplier_evaluation_dto.remark}};
}

// ORM mapping
namespace model {
template <>
struct ReflectTable<SupplierEvaluationDTO, db::supplier_evaluation> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&SupplierEvaluationDTO::id, &db::supplier_evaluation::id),
    std::make_pair(&SupplierEvaluationDTO::evaluation_id,
                   &db::supplier_evaluation::evaluation_id),
    std::make_pair(&SupplierEvaluationDTO::supplier_rk_id,
                   &db::supplier_evaluation::supplier_rk_id),
    std::make_pair(&SupplierEvaluationDTO::evaluation_date,
                   &db::supplier_evaluation::evaluation_date),
    std::make_pair(&SupplierEvaluationDTO::service_score,
                   &db::supplier_evaluation::service_score),
    std::make_pair(&SupplierEvaluationDTO::qualify_score,
                   &db::supplier_evaluation::qualify_score),
    std::make_pair(&SupplierEvaluationDTO::timeliness_score,
                   &db::supplier_evaluation::timeliness_score),
    std::make_pair(&SupplierEvaluationDTO::total_score,
                   &db::supplier_evaluation::total_score),
    std::make_pair(&SupplierEvaluationDTO::comment,
                   &db::supplier_evaluation::comment),
    std::make_pair(&SupplierEvaluationDTO::remark,
                   &db::supplier_evaluation::remark));
};

// mapping
template <typename Supplier_evaluationRow>
struct ReflectTableRow<SupplierEvaluationDTO, Supplier_evaluationRow> {
  static SupplierEvaluationDTO assign_model(Supplier_evaluationRow&& row)
  {
    return SupplierEvaluationDTO{.id = row.id,
                                 .evaluation_id = row.evaluation_id,
                                 .supplier_rk_id = row.supplier_rk_id,
                                 .evaluation_date = row.evaluation_date,
                                 .service_score = row.service_score,
                                 .qualify_score = row.qualify_score,
                                 .timeliness_score = row.timeliness_score,
                                 .total_score = row.total_score,
                                 .comment = row.comment,
                                 .remark = row.remark};
  }
};
}  // namespace model
