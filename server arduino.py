from flask import Flask, request, jsonify
app = Flask(__name__)



# datas = 0

@app.route('/api/add_message/<uuid>', methods=['GET', 'POST'])
def add_message(uuid):
    print("pesan dari :", uuid)
    content = request.json
    print(content)
    f = open("C:/Users/Alienware M17/Desktop/coding/server nonton anime/data.txt", "r")
    # f.write(f"{data}")
    # f.read()
    bagus = f.read()
    return f"{bagus}"

@app.route('/')
def des():
    return """
    <!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
.switch {
  position: relative;
  display: inline-block;
  width: 60px;
  height: 34px;
}

.switch input { 
  opacity: 0;
  width: 0;
  height: 0;
}

.slider {
  position: absolute;
  cursor: pointer;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #ccc;
  -webkit-transition: .4s;
  transition: .4s;
}

.slider:before {
  position: absolute;
  content: "";
  height: 26px;
  width: 26px;
  left: 4px;
  bottom: 4px;
  background-color: white;
  -webkit-transition: .4s;
  transition: .4s;
}

input:checked + .slider {
  background-color: #2196F3;
}

input:focus + .slider {
  box-shadow: 0 0 1px #2196F3;
}

input:checked + .slider:before {
  -webkit-transform: translateX(26px);
  -ms-transform: translateX(26px);
  transform: translateX(26px);
}

/* Rounded sliders */
.slider.round {
  border-radius: 34px;
}

.slider.round:before {
  border-radius: 50%;
}
</style>
</head>
    <body style="background-color:#33475b">
    <div style="position: absolute; top: 40vh;left: 45vw;">
    <p style="color: rgb(255,255,255)">hidup kan merah?</p>
    <label style="margin-left:20%;" class="switch">
    <input class="merah" type="checkbox">
    <span class="slider round" onclick='{if(!(document.querySelector(".merah").checked)){
        fetch("http:\/\/127.0.0.1:5000/yes/12", {method: "GET"})
        }
        else{
        fetch("http:\/\/127.0.0.1:5000/yes/21", {method: "GET"})
        }
        }'></span>
    </label>
    </div>
    </html>
    """
# {fetch("http://127.0.0.1:5000/yes/"+input.value, {method: "GET"})}}
@app.route('/yes/<data>')
def ubah(data):
    f = open("C:/Users/Alienware M17/Desktop/coding/server nonton anime/data.txt", "w")
    f.write(f"{data}")
    f.close()
    return jsonify({"lol":"ya"})

# @app.route('/yes1/<data>')
# def ubah(data):
#     f = open("C:/Users/Alienware M17/Desktop/coding/server nonton anime/data1.txt", "w")
#     f.write(f"{data}")
#     f.close()
#     return jsonify({"lol":"ya"})


if __name__ == '__main__':
    app.run(host= '0.0.0.0',port=5000,debug=True)