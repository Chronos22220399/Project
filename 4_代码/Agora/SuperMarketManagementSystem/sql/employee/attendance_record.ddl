-- 考勤记录表
-- status 字段含义：
--   present       : 正常
--   late          : 迟到
--   early_leave   : 早退
--   absent        : 缺勤
-- leave_type 字段含义（仅当 status = 'absent' 时填写）：
--   sick_leave    : 病假
--   personal_leave: 事假
--   annual_leave  : 年假
--   other         : 其他
CREATE TABLE IF NOT EXISTS attendance_record (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  record_id TEXT NOT NULL UNIQUE,
  employee_rk_id INTEGER NOT NULL,
  date DATE NOT NULL,
  clock_in DATETIME NOT NULL,
  clock_out DATETIME,
  status TEXT NOT NULL CHECK (
    status IN ('present', 'late', 'early_leave', 'absent')
  ),
  leave_type TEXT CHECK (
    leave_type IS NULL
    OR leave_type IN (
      'sick_leave',
      'personal_leave',
      'annual_leave',
      'other'
    )
  ),
  remark TEXT,
  FOREIGN KEY (employee_rk_id) REFERENCES employee (id),
  UNIQUE (employee_rk_id, date)
);
