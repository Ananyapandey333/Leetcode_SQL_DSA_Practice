SELECT d.name AS Department, e.name AS Employee, e.salary AS Salary
FROM Employee e
JOIN Department d ON e.departmentId = d.id
WHERE (e.departmentId, e.salary) IN (
    SELECT departmentId, salary
    FROM (
        SELECT DISTINCT departmentId, salary 
        FROM Employee
    ) AS UniqueSalaries
    WHERE salary >= (
        SELECT MIN(salary)
        FROM (
            SELECT DISTINCT salary 
            FROM Employee 
            WHERE departmentId = UniqueSalaries.departmentId
            ORDER BY salary DESC 
            LIMIT 3
        ) AS TopThree
    )
);