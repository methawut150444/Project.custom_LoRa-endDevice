const express = require('express')
const bodyParser = require('body-parser');
const getIn_Route = require("./src/routes")

const app = express();


app.use(express.json());
app.use(bodyParser.json());

app.get('/', (req, res)=>{
    res.send('use the URL api path: "/api/v1/independentStudy/" ');
})

app.use("/api/v1/independentStudy/", getIn_Route)

const port = 3301
app.listen(port, ()=>{
    console.log(`Server is now listening at port ${port}`);
    
})

//! http://feb-by.gl.at.ply.gg:64487
