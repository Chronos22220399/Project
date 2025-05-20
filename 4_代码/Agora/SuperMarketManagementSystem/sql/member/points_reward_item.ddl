CREATE TABLE IF NOT EXISTS redeemable_items (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    points_required INTEGER NOT NULL,
    quantity INTEGER NOT NULL,
    begin_time DATETIME NOT NULL,
    end_time DATETIME NOT NULL,
    FOREIGN KEY (id) REFERENCES items(id)
);