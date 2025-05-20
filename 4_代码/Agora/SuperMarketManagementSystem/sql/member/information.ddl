CREATE TABLE IF NOT EXISTS members (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    phone TEXT UNIQUE NOT NULL,
    gender TEXT,
    birthday DATE,
    level_id INTEGER,
    points INTEGER DEFAULT 0,
    registration_date DATE NOT NULL,
    FOREIGN KEY (level_id) REFERENCES member_levels(id)
);