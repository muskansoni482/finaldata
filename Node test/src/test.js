import routes from "./api/route/routes";
import express from "express";
let app = express(),
  port = process.env.PORT || 3000,
  mongoose = require('mongoose'),
  cors = require('cors'),
  Task = require('./api/model/models'), //created model loading here
  bodyParser = require('body-parser');
  app.use(cors());
  //////////////////////
  const path = require('path');
  const pug = require('pug');
  app.set('views',path.join(__dirname,'views'));
  app.set('view engine', 'pug')

  ///////////////////////
// mongoose instance connection url connection
mongoose.Promise = global.Promise;
mongoose.connect('mongodb://localhost:27017/tester'); 

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
//app.use(express.urlencoded({ extended: true }))
routes(app); //register the route


app.listen(port,()=>{
  console.log('todo list RESTful API server started on: ' + port);
});


