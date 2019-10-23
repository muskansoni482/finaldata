const IPFS = require('ipfs')
const node = new IPFS();
var ip = require("ip");
const keyPublishable = 'pk_test_RGKE2mOXdpAWa6N5Spq5YZkj00HMJcaaEI';
const keySecret = 'sk_test_v5Ui9V92tGJtv5c5mxKxhwd900EwlbhrlT';
const stripe = require("stripe")(keySecret);
// var ipfsClient = require('ipfs-http-client');
// var ipfs = ipfsClient('ipfs.infura.io', '5001', {protocol: 'https'})
const multer = require("multer");
const Tasks = require('../model/models');
const Business = require('../model/models');
var axios = require("axios")
exports.list_all_tasks = function(req, res) {
Tasks.find({}, function(err, task) {
  console.log("error-->",err)
  console.log("data-->",task)
console.dir ( ip.address() );
  if (err)
    res.send(err);
  res.json(task);
});
};

exports.create_a_task = function(req, res) {
var datalen=req.body.jobStatus.length
var jobStatus=[]
for(var i=0;i<datalen;i++) {
  console.log("data-->",i)
  jobStatus.push({
    email:req.body.jobStatus[i].email,
    userstatus:req.body.jobStatus[i].userstatus
  })
}
console.log("data-->",jobStatus)
const new_task = new Tasks({name:req.body.name,jobStatus:jobStatus
});
new_task.save(function(err, task) {
  if (err)
    res.send(err);
  res.json(task);
});
};


exports.read_a_task = function(req, res) {
Tasks.findOne({name:req.params.name}, function(err, task) {
  if (err)
    res.send(err);
  res.json(task);
});
};


exports.update_a_task = function(req, res) {
Tasks.findOneAndUpdate({name:req.body.name},{name:req.body.newname}, function(err, task) {
  if (err)
    res.send(err);
  res.json({message: 'Task successfully Updated'});
});
};


exports.delete_a_task = function(req, res) {
Tasks.remove({
  name: req.params.name
}, function(err, task) {
  if (err)
    res.send(err);
  res.json({ message: 'Task successfully deleted' });
});
};
exports.raven_method = (req, res) =>{
  try{

    axios.post("http://__cookie__:b899b8b5b3ef4a975ad143ea336644b8398eb324a53da883cd7031066800380d@127.0.0.1:8766/",
    {
     "jsonrpc": "1.0",
     "id":"curltest",
     "method": "getwalletinfo",
     "params": [] 
     
   }).then((response)=>{
   console.log("response-->",response.data.result)
   res.json(response.data.result)
    })
  }catch(err){
    console.log("error in code -->",err)
  }
  };
  exports.get_data=(req,res)=>{
    console.log("request-->",req.body.ipfsPath)
    try{
      node.cat(req.body.ipfsPath, function (err, file) {
        if (err) {
          throw err
        }
        // res.json(file.toString('utf8'))
        console.log("filedata",file)
      })
        // ipfs.get(req.body.hash, function (err, data) {
        //   if(!err){
        //     res.json(data)
        //   }
        //   console.log("data-->",data)
        // })
        // node.swarm.peers(function (err, peerInfos) {
        //   if (err) {
        //     throw err
        //   }else{
        //     node.swarm.connect(peerInfos[0].addr, function (err) {
        //       if (err) {
        //         throw err
        //       }
        //     res.json(peerInfos)
        //     })
        //   }
        //   console.log(peerInfos)
        // })
    }catch(err){
        console.log("err->",err)
    }
  }
  exports.ipfs_task=(req,res)=>{
      try{
          upload(req, res, (err) => {
            console.log(req,"Request file ---", req.file);//Here you get file.
            const files = [
                {
                  content: req.file.buffer
                }
              ]
             console.log("Request ---", files);
             node.add(files).then(results=>{
              console.log(results)
              const new_entry = new Business({Businessname:req.file.originalname,Logohash:results[0].hash
              });
              new_entry.save(function(err, entry) {
                if (err)
                  res.send(err);
                res.json(entry);
              });
            })
          });
      }catch(err){
        console.log(err);

      }
  }
exports.stripecode=(req,res)=>{
  stripe.plans.create({
    amount: 5000,
    interval: "month",
    product: {
      name: "Equa ref"
    },
    currency: "usd",
  }, function(err, plan) {
    console.log("plan-->",plan)
    // asynchronously called
  });
  stripe.subscriptions.create({
    customer: "cus_FBb8D9d61QtBD8",
    items: [
      {
        plan: "plan_FBboVcMzFEqnXR"
      },
    ]
  }, function(err, subscription) {
    console.log("subs->",subscription)
      // asynchronously called
    }
  );
  // var month=req.body.expirationDate.split("/")[0]
  // var year=req.body.expirationDate.split("/")[1]
  // var cardno=req.body.cardNumber;
  // var CVC=req.body.CVC;
  // console.log(year,"data->",month)
  // stripe.tokens.create({
  //   card: {
  //     number: cardno,
  //     exp_month: month,
  //     exp_year: year,
  //     cvc: CVC
  //   }
  // }, function(err, token) {
  //   console.log("tokenid->",token)
  // stripe.customers.create({
  //     email: req.body.stripeEmail, // customer email, which user need to enter while making payment
  //     // source:"tok_1EhCxdGwRI2O6qPQJn4ei8LS" // token for the given card 
  //     source:token.id
  // }).then((customer)=>{
  //   console.log("customer->",customer)
  //   stripe.charges.create({ // charge the customer
  //     amount:2000,
  //     description: "Sample Charge",
  //     currency: "usd",
  //     customer: customer.id
  // })
  // .then(charge => console.log("charge",charge)); 
  // })
  // });
 
} 
 const upload = multer({
    // storage: storage,
    limits:{fileSize: 1000000},
 }).single("filename");