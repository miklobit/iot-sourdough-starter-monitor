from flask import Flask, render_template, request, jsonify
import pandas as pd
import numpy as np
from random import randint

app = Flask(__name__)


@app.route("/")
def hello():
    return render_template("index.html")


@app.route("/get_data", methods=["post"])
def get_data():
    start_date, start_time = request.form["start"].split()
    end_date, end_time = request.form["end"].split()
    print(start_date, start_time)

    df = pd.read_json("data.json")

    # Randomize horizontal axis
    df = df.iloc[: randint(10, df.shape[0])]
    # Randomize data
    df["date"] = df["date"].dt.strftime("%Y-%m-%d")
    df["distance"] = df["distance"] * np.random.randint(0, 100, df.shape[0])
    df["temperature"] = df["temperature"] * np.random.randint(0, 100, df.shape[0])
    df["humidity"] = df["humidity"] * np.random.randint(0, 100, df.shape[0])

    data_out = {}

    for col in ["distance", "temperature", "humidity"]:
        # Output data must have column names "date" and "value" for d3 charts
        data_out[col] = (
            df[["date", col]].rename(columns={col: "value"}).to_json(orient="records")
        )

    return jsonify(data_out)


if __name__ == "__main__":
    app.run()
