import { StyleSheet, Text, View, ImageBackground } from "react-native";
import { useEffect, useState } from "react";

import { db, ref, onValue } from "../firebase";  //

import background from "../assets/background1.png";

const Interface = () => {
  const [flame, setFlame] = useState(false);
  const [ultrasonic, setUltrasonic] = useState(0);
  const [waterLevel, setWaterLevel] = useState(0);

  useEffect(() => {
    const data = ref(db);
    onValue(data, (snapshot) => {
      setFlame(snapshot.val().flame);
      setUltrasonic(snapshot.val().ultrasonic);
      setWaterLevel(snapshot.val().waterlevel); 
    });
  }, [db]);
  return (
    <ImageBackground source={background} style={styles.container}>
      <View style={styles.data}>
        <View style={styles.spacer}></View>
        <View style={styles.dataWrapper}>
          <View style={styles.humid}>
            <Text style={styles.dataText}>{ultrasonic}</Text>
            <Text style={styles.title}>Distance (cm)</Text>
          </View>
          <View style={styles.humid}>
            <Text style={styles.dataText}>{waterLevel}</Text>
            <Text style={styles.title}>Water Level (cm)</Text>
          </View>
          <View style={styles.pressure}>
            <Text style={styles.dataText}>{flame ? "Yes" : "No"}</Text>
            <Text style={styles.title}>Flame</Text>
          </View>
        </View>
      </View>
    </ImageBackground>
  );
};

export default Interface;

const styles = StyleSheet.create({
  container: {
    flex: 1,
    resizeMode: "cover",
    justifyContent: "center",
    //image blur
    backgroundColor: "rgba(0, 0, 0, 0.3)",
  },
  tempWrapper: {
    flex: 1,
    justifyContent: "center",
  },
  text: {
    fontSize: 150,
    fontWeight: "100",
    textAlign: "right",
    color: "black",
    paddingRight: 35,
  },
  data: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
    width: "100%",
  },

  dataWrapper: {
    backgroundColor: "rgba(255, 255, 255, 0.4)",
    flexDirection: "row",
    height: "20%",
    justifyContent: "center",
    alignItems: "center",
    width: "80%",
    borderRadius: 20,
    borderWidth: 1,
    borderColor: "black",
  },

  humid: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
  },
  pressure: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
  },
  dataText: {
    fontSize: 30,
    fontWeight: "500",
    color: "black",
    textAlign: "center"
  },
  title: {
    fontSize: 13,
    fontWeight: "bold",
    color: "black",
    textAlign: "center"
  },
});
