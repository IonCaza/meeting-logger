import React from 'react';
import ReactDOM from 'react-dom';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';
import PageIncrement from './components/PageIncrement';

ReactDOM.render(
  <Router>
    <Switch>
      <Route exact path="/" component={PageIncrement} />
    </Switch>
  </Router>,
  document.getElementById('root')
);
