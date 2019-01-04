import axios from 'axios';

export default function login(username, password) {
  console.log(username, ' ', password);
  axios.get(`https://jsonplaceholder.typicode.com/users`).then(res => {
    const persons = res.data;
    console.log(persons);
  });
}
