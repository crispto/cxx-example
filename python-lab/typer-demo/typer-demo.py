import typer
import sqlite3

app = typer.Typer()

# Create a SQLite database connection
conn = sqlite3.connect("tasks.db")
cursor = conn.cursor()

# Create a table to store tasks if it doesn't exist
cursor.execute(
    """
    CREATE TABLE IF NOT EXISTS tasks (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        task TEXT
    )
    """
)
conn.commit()

@app.command()
def add_task(task: str):
    """Add a new task to the list."""
    cursor.execute("INSERT INTO tasks (task) VALUES (?)", (task,))
    conn.commit()
    typer.echo(f"Added task: {task}")

@app.command()
def list_tasks():
    """List all tasks."""
    cursor.execute("SELECT * FROM tasks")
    tasks = cursor.fetchall()

    if tasks:
        typer.echo("Tasks:")
        for task in tasks:
            typer.echo(f"{task[0]}. {task[1]}")
    else:
        typer.echo("No tasks to display.")

if __name__ == "__main__":
    app()
