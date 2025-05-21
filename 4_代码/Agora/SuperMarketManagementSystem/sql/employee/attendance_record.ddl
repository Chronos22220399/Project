-- 考勤
CREATE TABLE IF NOT EXISTS attendance_record (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  attendance_id TEXT NOT NULL,
  employee_id TEXT NOT NULL,
  date DATE NOT NULL,
  dock_in DATETIME NOT NULL,
  dock_out DATETIME,
  status TEXT NOT NULL CHECK (status IN ('正常', '迟到', '早退', '缺勤')),
  leave_type TEXT,
  remark TEXT,
  FOREIGN KEY (employee_id) REFERENCES employee (employee_id),
  UNIQUE (employee_id, date)
);
