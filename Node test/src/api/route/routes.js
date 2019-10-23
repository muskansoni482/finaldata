module.exports = function(router) {
    const todoList = require('../controller/controllers');
    // todoList Routes
    router.get('/tasks',(req,res)=>{
      todoList.list_all_tasks(req,res)
    })
    router.post('/create',(req,res)=>{
      todoList.create_a_task(req,res)
    })
    router.get('/read/:name',(req,res)=>{
      todoList.read_a_task(req,res)
    })
    router.post('/update',(req,res)=>{
      todoList.update_a_task(req,res)
    })
    router.get('/delete/:name',(req,res)=>{
      todoList.delete_a_task(req,res)
    })
    router.get('/raventask',(req,res)=>{
      todoList.raven_method(req,res)
    })
    router.post('/ipfstask',(req,res)=>{
      todoList.ipfs_task(req,res)
    })
    router.post('/getdata',(req,res)=>{
      todoList.get_data(req,res)
    })
    router.post('/charge',(req,res)=>{
      todoList.stripecode(req,res)
    })
  };
  //const express= require("express")
  // import express from 'express';
  // import todoList from '../controller/controllers';
  // //const todoList = require('../controller/controllers');
  // const router = express.Router();
  // // todoList Routes
  // router.get('/tasks',(req,res)=>{
  //   todoList.list_all_tasks(req,res)
  // })
  // router.post('/create',(req,res)=>{
  //   todoList.create_a_task(req,res)
  // })
  // router.get('/read/:name',(req,res)=>{
  //   todoList.read_a_task(req,res)
  // })
  // router.post('/update',(req,res)=>{
  //   todoList.update_a_task(req,res)
  // })
  // router.get('/delete/:name',(req,res)=>{
  //   todoList.delete_a_task(req,res)
  // })
  // router.get('/raventask',(req,res)=>{
  //   todoList.raven_method(req,res)
  // })

  // export default router;