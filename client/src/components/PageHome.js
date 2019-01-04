import React, { Component } from 'react';
import PropTypes from 'prop-types';
import { withStyles } from '@material-ui/core/styles';

import Grid from '@material-ui/core/Grid';
import Typography from '@material-ui/core/Typography';

import Layout from './NavLayout';

import Credentials from './FunctionCredentials.js';
import LoginForm from './WidgetLoginForm';

const styles = theme => ({
  root: {
    flexGrow: 1,
    overflow: 'hidden',
    position: 'relative',
    display: 'flex',
    width: '100%',
  },
  mainHeadline: {
    paddingTop: theme.spacing.unit * 2,
  },
  component: {
    backgroundColor: '#CCC',
    paddingTop: theme.spacing.unit * 2,
    paddingLeft: theme.spacing.unit * 2,
    paddingRight: theme.spacing.unit * 2,
    paddingBottom: theme.spacing.unit * 2,
  },
});

class PageHome extends Component {
  render() {
    const { classes, loginToken } = this.props;

    const homeObject = (
      <Grid container spacing={0} className={classes.root}>
        <Grid item md={4} />
        <Grid item md={4} xs={12} className={classes.component}>
          <Typography variant="display1" gutterBottom className={classes.mainHeadline}>
            meetloaf-0.1
          </Typography>
          <Typography variant="caption">{loginToken ? 'loggedin' : 'notloggedin'}</Typography>
          {loginToken ? '' : <LoginForm />}
          <button type="submit" onClick={this.getCredentials(1, 2)}>
            Activate Lasers
          </button>
        </Grid>
        <Grid item md={4} />
      </Grid>
    );

    return <Layout>{homeObject}</Layout>;
  }

  getCredentials = (username, password) => {
    Credentials.login(username, password);
  };
}

PageHome.propTypes = {
  classes: PropTypes.object.isRequired,
  loginToken: PropTypes.string,
};

PageHome.defaultProps = {
  loginToken: '',
};

export default withStyles(styles)(PageHome);
