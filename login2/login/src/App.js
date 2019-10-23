import React, { Component } from 'react';
import './App.css';
import ScatterJS from "scatterjs-core";
import ScatterEOS from "scatterjs-plugin-eosjs2"; 
import { Api, JsonRpc} from 'eosjs';
ScatterJS.plugins(new ScatterEOS());
var scatter = {};
const network = {
  protocol: "https", // Defaults to https
  blockchain: "eos",
  host: "jungle2.cryptolions.io",
  port: 443,
  chainId: "e70aaab8997e1dfce58fbfac80cbbb8fecec7b99cf982a9444273cbc64c41473"
};
const eosOptions = {
  chainId: "e70aaab8997e1dfce58fbfac80cbbb8fecec7b99cf982a9444273cbc64c41473"
};
const endpoint = 'https://jungle2.cryptolions.io:443';
class App extends Component {
  constructor() {
    super();
    this.state = {
      loginstatus: "LOGIN",
      status: false
    }
    this.login = this.login.bind(this);
  }

  componentWillMount() {
    ScatterJS.scatter.connect('equa-dapp').then((connected) => {
      scatter = ScatterJS.scatter;
      
      if (connected) {
        if (scatter.identity) {
          console.log("1-scatter")
          const acc = scatter.identity.accounts[0];
          const account = acc.name;
          localStorage.setItem("username", account);
          localStorage.setItem("status", true);
          this.setState({
            loginstatus: "LOGOUT",
            status: true
          })
        } else {
          console.log("scatter")
          localStorage.setItem("username", "");
          localStorage.setItem("status", false);
          this.setState({
            loginstatus: "LOGIN",
            status: false
          })
        }

      } else {
        console.log("scatter not installed")
      }
    })
  }
  async login() {
    if (!this.state.status) {
      console.log("1-------------------")
      ScatterJS.scatter.connect('equa-dapp').then(connected => {
        if (!connected) return false;
        scatter = ScatterJS.scatter;
        const requiredFields = { accounts: [network] };
        const rpc = new JsonRpc(endpoint);
        this.eos = scatter.eos(network, Api, { rpc });
        scatter.getIdentity(requiredFields).then((res) => {
          const acc = scatter.identity.accounts.find(x => x.blockchain === 'eos');
          const account = acc.name;
          localStorage.setItem("username", account);
          localStorage.setItem("status", true);
          this.setState({
            loginstatus: "LOGOUT",
            status: true
          })
          console.log("enter")
        }).catch(error => {
          console.error(error);
        });
      });
    } else {
      console.log("2-----------------")
      scatter.forgetIdentity().then(() => {
        localStorage.setItem("username", "");
        localStorage.setItem("status", false);
        this.setState({
          loginstatus: "LOGIN",
          status: false
        })

      });
    }

  }

  render() {
    return (
      <div className="App">
       <button onClick={this.login}>{this.state.loginstatus}</button>
      </div>
    );
  }
}

export default App;
