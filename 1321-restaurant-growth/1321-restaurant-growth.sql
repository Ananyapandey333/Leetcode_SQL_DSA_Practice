WITH DailyTotals AS (
    SELECT visited_on, SUM(amount) AS daily_amount
    FROM Customer
    GROUP BY visited_on
)
SELECT 
    a.visited_on AS visited_on,
    SUM(b.daily_amount) AS amount,
    ROUND(SUM(b.daily_amount) / 7.0, 2) AS average_amount
FROM DailyTotals a
JOIN DailyTotals b 
  ON b.visited_on BETWEEN a.visited_on - INTERVAL 6 DAY AND a.visited_on
GROUP BY a.visited_on
HAVING COUNT(b.visited_on) = 7
ORDER BY a.visited_on ASC;