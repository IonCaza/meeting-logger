import React from 'react';
import PropTypes from 'prop-types';
import { withStyles } from '@material-ui/core/styles';

const styles = () => ({
  loginForm: {
    textSize: '10px',
  },
});

const LoginForm = props => {
  const { classes } = props;

  const componentLoginForm = <div className={classes.loginForm}>Login Form!</div>;

  return componentLoginForm;
};

LoginForm.propTypes = {
  classes: PropTypes.object.isRequired,
};

export default withStyles(styles)(LoginForm);
