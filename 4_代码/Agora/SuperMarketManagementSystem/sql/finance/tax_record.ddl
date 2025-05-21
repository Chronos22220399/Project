-- 税务记录表
-- Tax Type（税种类型）：
-- 'vat' : 增值税
-- 'corporate' : 企业所得税 
-- 'personal' : 个人所得税
-- 'consumption' : 消费税
-- 'property' : 房产税
-- 'land_use' : 土地使用税
-- 'stamp_duty' : 印花税
CREATE TABLE IF NOT EXISTS tax_record (
  id INTEGER PRIMARY KEY AUTOINCREMENT, -- Internal ID（自增主键，内部使用）
  record_id TEXT NOT NULL UNIQUE, -- Tax Record ID（税务记录ID，外部使用，UUID）
  tax_type TEXT NOT NULL CHECK (
    tax_type IN (
      'vat',
      'corporate',
      'personal',
      'consumption',
      'property',
      'land_use',
      'stamp_duty'
    )
  ),
  tax_period TEXT NOT NULL, -- Tax Period（报税周期）
  tax_payable REAL NOT NULL CHECK (tax_payable >= 0), -- Tax Payable（应缴税金额）
  tax_paid REAL NOT NULL CHECK (tax_paid >= 0), -- Tax Paid（实缴税金额）
  report_rk_id INTEGER NOT NULL, -- Report ID（财务报表ID）
  declared_by INTEGER NOT NULL, -- Declared By（申报人ID）
  status TEXT NOT NULL CHECK (status IN ('declared', 'pending', 'paid')), -- Tax Status（税务状态：已申报、待申报、已缴）
  paid_at DATETIME, -- Paid Time（缴税时间）
  FOREIGN KEY (report_rk_id) REFERENCES financial_report (id) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY (declared_by) REFERENCES employee (id) ON DELETE RESTRICT ON UPDATE CASCADE
);
