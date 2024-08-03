import { initializeApp } from "firebase/app";
import { getDatabase, ref, onValue } from "firebase/database";

// Your web app's Firebase configuration
const firebaseConfig = {
  apiKey: "AIzaSyBOgjbAMIKzmZV3TN3xFtf1-_KBrenIgF4",
  authDomain: "smart-white-cane-67105.firebaseapp.com",
  databaseURL: "https://smart-white-cane-67105-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "smart-white-cane-67105",
  storageBucket: "smart-white-cane-67105.appspot.com",
  messagingSenderId: "620671365747",
  appId: "1:620671365747:web:5aa19213d4d9d468537006"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const db = getDatabase(app);

export { db, ref, onValue };