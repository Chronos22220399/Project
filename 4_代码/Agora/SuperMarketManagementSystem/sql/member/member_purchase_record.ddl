CREATE TABLE IF NOT EXISTS member_transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    member_id INTEGER NOT NULL,
    transaction_date DATE NOT NULL,
    amount DECIMAL(10, 2) NOT NULL CHECK (amount >= 0),
    earned_points INTEGER NOT NULL,
    FOREIGN KEY (member_id) REFERENCES members(id)
);