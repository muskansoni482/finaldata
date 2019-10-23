var mongoose = require('mongoose');
var Schema = mongoose.Schema;


var TaskSchema = new Schema({
  name: {
    type: String,
    // required: 'Kindly enter the name of the task'
  },
  jobStatus:[
    {
      email:{
      type:String
      },
      userstatus:{
      type:Boolean
      }
    }
  ],
  Created_date: {
    type: Date,
    default: Date.now
  },
  status: {
    type: [{
      type: String,
      enum: ['pending', 'ongoing', 'completed']
    }],
    default: ['pending']
  }
});

var BusinessSchema = new Schema({
  Businessname: {
    type: String
    // required: 'Kindly enter the name of the task'
  },
  Logohash:{
    type:String
  }
});

module.exports = mongoose.model('Tasks', TaskSchema);
module.exports = mongoose.model('Business', BusinessSchema);
