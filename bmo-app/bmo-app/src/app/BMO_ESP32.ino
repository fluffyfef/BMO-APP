import React, { useState, useEffect } from 'react';
import { StyleSheet, Text, View, Switch, ScrollView, SafeAreaView, Platform, StatusBar } from 'react-native';
import { initializeApp } from 'firebase/app';
import { getDatabase, ref, onValue, update } from 'firebase/database';

// 1. COLOCAR SUAS CREDENCIAIS DO FIREBASE AQUI
// (Você pega isso no painel do Firebase após criar o projeto)
const firebaseConfig = {
  apiKey: "SUA_API_KEY",
  authDomain: "seu-projeto.firebaseapp.com",
  databaseURL: "https://seu-projeto-default-rtdb.firebaseio.com",
  projectId: "seu-projeto",
  storageBucket: "seu-projeto.appspot.com",
  messagingSenderId: "SEU_SENDER_ID",
  appId: "SEU_APP_ID"
};

// 2. INICIALIZAR O FIREBASE
const app = initializeApp(firebaseConfig);
const db = getDatabase(app);

export default function App() {
  // Estados dos sensores
  const [temp, setTemp] = useState('0.0');
  const [hum, setHum] = useState(0);
  const [co2, setCo2] = useState(0);

  // Estados dos atuadores
  const [nevoa, setNevoa] = useState(false);
  const [exaustor, setExaustor] = useState(false);
  const [luz, setLuz] = useState(false);

  // 3. LER DADOS DO FIREBASE EM TEMPO REAL
  useEffect(() => {
    // Referência para os sensores na nuvem
    const sensoresRef = ref(db, 'estufa_01/sensores');
    onValue(sensoresRef, (snapshot) => {
      const data = snapshot.val();
      if (data) {
        setTemp(data.temperatura);
        setHum(data.umidade);
        setCo2(data.co2);
      }
    });

    // Referência para os atuadores na nuvem (para manter sincronizado se mudar fisicamente)
    const atuadoresRef = ref(db, 'estufa_01/atuadores');
    onValue(atuadoresRef, (snapshot) => {
      const data = snapshot.val();
      if (data) {
        setNevoa(data.nevoa);
        setExaustor(data.exaustor);
        setLuz(data.luz);
      }
    });
  }, []);

  // 4. FUNÇÕES PARA ENVIAR COMANDOS PARA A NUVEM E PARA O ESP32
  const toggleNevoa = async (valor) => {
    setNevoa(valor);
    await update(ref(db, 'estufa_01/atuadores'), { nevoa: valor });
  };

  const toggleExaustor = async (valor) => {
    setExaustor(valor);
    await update(ref(db, 'estufa_01/atuadores'), { exaustor: valor });
  };

  const toggleLuz = async (valor) => {
    setLuz(valor);
    await update(ref(db, 'estufa_01/atuadores'), { luz: valor });
  };

  const emAlerta = co2 > 800;

  return (
    <SafeAreaView style={styles.safeArea}>
      <ScrollView contentContainerStyle={styles.container}>
        
        {/* Header BMO */}
        <View style={styles.header}>
          <View>
            <Text style={styles.headerTitle}>B.M.O.</Text>
            <Text style={styles.headerSubtitle}>Bio-Monitoramento Operacional</Text>
          </View>
          <View style={styles.avatar}>
            <Text style={styles.avatarIcon}>🎮</Text>
          </View>
        </View>

        {/* Banner de Status */}
        <View style={[styles.statusBanner, emAlerta && styles.statusBannerAlert]}>
          <Text style={[styles.statusText, emAlerta && styles.statusTextAlert]}>
            {emAlerta ? '🚨 Alerta de CO2!' : '✨ Clima Perfeito!'}
          </Text>
        </View>

        {/* Grid de Sensores */}
        <View style={styles.grid}>
          <View style={styles.card}>
            <Text style={styles.cardIcon}>🌡️</Text>
            <Text style={styles.cardTitle}>TEMP</Text>
            <Text style={styles.cardValue}>{temp} <Text style={styles.cardUnit}>°C</Text></Text>
          </View>
          
          <View style={styles.card}>
            <Text style={styles.cardIcon}>💧</Text>
            <Text style={styles.cardTitle}>UMIDADE</Text>
            <Text style={styles.cardValue}>{hum} <Text style={styles.cardUnit}>%</Text></Text>
          </View>

          <View style={[styles.card, styles.cardFull]}>
            <Text style={styles.cardIcon}>🍄</Text>
            <View style={styles.cardFullText}>
              <Text style={styles.cardTitle}>NÍVEL DE CO2</Text>
              <Text style={styles.cardValue}>{co2} <Text style={styles.cardUnit}>ppm</Text></Text>
            </View>
          </View>
        </View>

        {/* Controles Manuais */}
        <View style={styles.controlsSection}>
          <Text style={styles.sectionTitle}>CONTROLES DA ESTUFA</Text>

          <View style={styles.controlItem}>
            <View style={styles.controlInfo}>
              <Text style={styles.controlIcon}>💦</Text>
              <Text style={styles.controlLabel}>Umidificador</Text>
            </View>
            <Switch
              trackColor={{ false: '#45A395', true: '#3EBCF0' }}
              thumbColor={nevoa ? '#ffffff' : '#FF4A5A'}
              onValueChange={toggleNevoa}
              value={nevoa}
            />
          </View>

          <View style={styles.controlItem}>
            <View style={styles.controlInfo}>
              <Text style={styles.controlIcon}>💨</Text>
              <Text style={styles.controlLabel}>Exaustor</Text>
            </View>
            <Switch
              trackColor={{ false: '#45A395', true: '#3EBCF0' }}
              thumbColor={exaustor ? '#ffffff' : '#FF4A5A'}
              onValueChange={toggleExaustor}
              value={exaustor}
            />
          </View>

          <View style={styles.controlItem}>
            <View style={styles.controlInfo}>
              <Text style={styles.controlIcon}>💡</Text>
              <Text style={styles.controlLabel}>Luz Fria</Text>
            </View>
            <Switch
              trackColor={{ false: '#45A395', true: '#3EBCF0' }}
              thumbColor={luz ? '#ffffff' : '#FF4A5A'}
              onValueChange={toggleLuz}
              value={luz}
            />
          </View>

        </View>
      </ScrollView>
    </SafeAreaView>
  );
}

// Estilização do BMO
const styles = StyleSheet.create({
  safeArea: { flex: 1, backgroundColor: '#5DC8B8', paddingTop: Platform.OS === 'android' ? StatusBar.currentHeight : 0 },
  container: { padding: 20 },
  header: { flexDirection: 'row', justifyContent: 'space-between', alignItems: 'center', marginBottom: 20 },
  headerTitle: { fontSize: 28, fontWeight: '900', color: '#153E45' },
  headerSubtitle: { fontSize: 14, fontWeight: '800', color: '#153E45', opacity: 0.8 },
  avatar: { width: 50, height: 50, backgroundColor: '#FFD23F', borderRadius: 15, justifyContent: 'center', alignItems: 'center', borderWidth: 3, borderColor: '#153E45', borderBottomWidth: 5 },
  avatarIcon: { fontSize: 24 },
  statusBanner: { backgroundColor: '#FFD23F', padding: 15, borderRadius: 16, alignItems: 'center', borderWidth: 3, borderColor: '#153E45', borderBottomWidth: 6, marginBottom: 25 },
  statusBannerAlert: { backgroundColor: '#FF4A5A', borderColor: '#D43140' },
  statusText: { fontWeight: '900', fontSize: 18, color: '#153E45' },
  statusTextAlert: { color: '#ffffff' },
  grid: { flexDirection: 'row', flexWrap: 'wrap', justifyContent: 'space-between', marginBottom: 30 },
  card: { backgroundColor: '#E0F2D8', width: '48%', padding: 15, borderRadius: 20, borderWidth: 3, borderColor: '#153E45', borderBottomWidth: 6, alignItems: 'center', marginBottom: 15 },
  cardFull: { width: '100%', flexDirection: 'row', justifyContent: 'flex-start', alignItems: 'center' },
  cardFullText: { marginLeft: 15 },
  cardIcon: { fontSize: 32, marginBottom: 5 },
  cardTitle: { fontSize: 12, fontWeight: '900', color: '#3A737A', marginBottom: 5 },
  cardValue: { fontSize: 32, fontWeight: '900', color: '#153E45' },
  cardUnit: { fontSize: 16 },
  controlsSection: { marginTop: 10 },
  sectionTitle: { fontSize: 18, fontWeight: '900', color: '#153E45', marginBottom: 15 },
  controlItem: { flexDirection: 'row', justifyContent: 'space-between', alignItems: 'center', backgroundColor: '#E0F2D8', padding: 18, borderRadius: 20, borderWidth: 3, borderColor: '#153E45', borderBottomWidth: 5, marginBottom: 15 },
  controlInfo: { flexDirection: 'row', alignItems: 'center' },
  controlIcon: { fontSize: 24, marginRight: 10 },
  controlLabel: { fontSize: 16, fontWeight: '900', color: '#153E45' }
});