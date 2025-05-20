CREATE TABLE IF NOT EXISTS point_redemptions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    member_id INTEGER NOT NULL,
    points_spent INTEGER NOT NULL,
    item_id INTEGER NOT NULL,
    redemption_time DATETIME NOT NULL,
    operator_id INTEGER,
    FOREIGN KEY (member_id) REFERENCES members(id),
    FOREIGN KEY (item_id) REFERENCES items(id),
    FOREIGN KEY (operator_id) REFERENCES operators(id)
);