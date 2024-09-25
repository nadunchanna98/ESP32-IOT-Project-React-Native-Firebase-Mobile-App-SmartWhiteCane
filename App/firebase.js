import { initializeApp } from "firebase/app";
import { getDatabase, ref, onValue } from "firebase/database";

// Your web app's Firebase configuration
const firebaseConfig = {
  apiKey: "####",
  authDomain: "####",
  databaseURL: "####",
  projectId: "####",
  storageBucket: "####",
  messagingSenderId: "####",
  appId: "####"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const db = getDatabase(app);

export { db, ref, onValue };