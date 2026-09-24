import React, { useState, useEffect } from 'react';
import { StyleSheet, Text, View, Switch, ScrollView, SafeAreaView, Platform, StatusBar, Alert, TouchableOpacity } from 'react-native';

export default function App() {
  // Estados dos sensores existentes
  const [temp, setTemp] = useState('24.5');
  const [hum, setHum] = useState(85);
  const [co2, setCo2] = useState(750);

  // NOVO: Estados do Reservatório de Água
  const [nivelAgua, setNivelAgua] = useState(100); // Começa em 100%
  const [alertaEnviado, setAlertaEnviado] = useState(false);

  // Estados dos atuadores
  const [nevoa, setNevoa] = useState(true);
  const [exaustor, setExaustor] = useState(false);
  const [luz, setLuz] = useState(false);

  // Simulação dos dados IoT
  useEffect(() => {
    const interval = setInterval(() => {
      // Atualiza os sensores antigos
      const tempAtual = (24.0 + (Math.random() * 1.5 - 0.5)).toFixed(1);
      setTemp(tempAtual);
      setHum(Math.floor(85 + (Math.random() * 5 - 2)));
      setCo2(Math.floor(750 + (Math.random() * 50 - 25)));

      // NOVO: Simula o aspersor consumindo água (cai 10% a cada ciclo para facilitar o teste)
      setNivelAgua((nivelAnterior) => {
        const novoNivel = nivelAnterior > 0 ? nivelAnterior - 10 : 0;

        // Dispara a notificação se chegar a 20% ou menos e o alerta ainda não tiver sido mostrado
        if (novoNivel <= 20 && !alertaEnviado) {
          Alert.alert(
            "⚠️ ALERTA DO B.M.O.",
            "O nível de água está muito baixo! Reabasteça o reservatório para manter os cogumelos felizes e úmidos.",
            [{ text: "Entendido!" }]
          );
          setAlertaEnviado(true); // Evita que a notificação fique "spammando" a cada segundo
        }
        return novoNivel;
      });

    }, 3000); // O ciclo roda a cada 3 segundos

    return () => clearInterval(interval);
  }, [alertaEnviado]);

  // Função para simular o reabastecimento físico do tanque
  const reabastecerAgua = () => {
    setNivelAgua(100);
    setAlertaEnviado(false);
    Alert.alert("💧 Glup, glup!", "Reservatório cheio! B.M.O. está pronto para continuar umidificando.");
  };

  return (
    <SafeAreaView style={styles.bmoCorpo}>
      <StatusBar barStyle="dark-content" />
      
      <ScrollView contentContainerStyle={styles.container}>
        {/* TELA DO B.M.O. */}
        <View style={styles.bmoTela}>
          <Text style={styles.tituloTela}>Monitoramento Fúngico</Text>
          
          <View style={styles.sensorGrid}>
            <View style={styles.sensorCard}>
              <Text style={styles.sensorLabel}>Temperatura</Text>
              <Text style={styles.sensorValor}>{temp}°C</Text>
            </View>
            <View style={styles.sensorCard}>
              <Text style={styles.sensorLabel}>Umidade</Text>
              <Text style={styles.sensorValor}>{hum}%</Text>
            </View>
            <View style={styles.sensorCard}>
              <Text style={styles.sensorLabel}>CO2</Text>
              <Text style={styles.sensorValor}>{co2} ppm</Text>
            </View>
            
            {/* NOVO: CARD DO NÍVEL DE ÁGUA */}
            <View style={[styles.sensorCard, nivelAgua <= 20 && styles.sensorAlerta]}>
              <Text style={[styles.sensorLabel, nivelAgua <= 20 && styles.textoAlerta]}>Nível de Água</Text>
              <Text style={[styles.sensorValor, nivelAgua <= 20 && styles.textoAlerta]}>{nivelAgua}%</Text>
            </View>
          </View>
        </View>

        {/* PAINEL DE BOTÕES DO B.M.O. */}
        <View style={styles.painelBotoes}>
          
          {/* Botão de Reabastecimento (Triângulo amarelo do BMO) */}
          <TouchableOpacity style={styles.botaoReabastecer} onPress={reabastecerAgua}>
            <Text style={styles.textoBotao}>REABASTECER ÁGUA</Text>
          </TouchableOpacity>

          <Text style={styles.tituloControles}>Atuadores Manuais</Text>
          
          <View style={styles.controleLinha}>
            <Text style={styles.controleLabel}>Aspersor / Névoa</Text>
            <Switch
              trackColor={{ false: "#767577", true: "#E73A4F" }}
              thumbColor={nevoa ? "#F8DE59" : "#f4f3f4"}
              onValueChange={setNevoa}
              value={nevoa}
            />
          </View>

          <View style={styles.controleLinha}>
            <Text style={styles.controleLabel}>Exaustor de CO2</Text>
            <Switch
              trackColor={{ false: "#767577", true: "#E73A4F" }}
              thumbColor={exaustor ? "#F8DE59" : "#f4f3f4"}
              onValueChange={setExaustor}
              value={exaustor}
            />
          </View>

          <View style={styles.controleLinha}>
            <Text style={styles.controleLabel}>Iluminação</Text>
            <Switch
              trackColor={{ false: "#767577", true: "#E73A4F" }}
              thumbColor={luz ? "#F8DE59" : "#f4f3f4"}
              onValueChange={setLuz}
              value={luz}
            />
          </View>
        </View>

      </ScrollView>
    </SafeAreaView>
  );
}

// Estilização (Estética B.M.O.)
const styles = StyleSheet.create({
  bmoCorpo: {
    flex: 1,
    backgroundColor: '#5DC8B8', // Verde-água clássico do corpo do BMO
    paddingTop: Platform.OS === 'android' ? StatusBar.currentHeight : 0,
  },
  container: {
    padding: 20,
    alignItems: 'center',
  },
  bmoTela: {
    backgroundColor: '#E4ECAE', // Verde clarinho da tela do BMO
    width: '100%',
    borderRadius: 20,
    padding: 20,
    borderWidth: 8,
    borderColor: '#1D2323',
    marginBottom: 30,
    shadowColor: "#000",
    shadowOffset: { width: 0, height: 4 },
    shadowOpacity: 0.3,
    shadowRadius: 5,
    elevation: 8,
  },
  tituloTela: {
    fontSize: 22,
    fontWeight: '900',
    color: '#1D2323',
    textAlign: 'center',
    marginBottom: 15,
    textTransform: 'uppercase',
    letterSpacing: 2,
  },
  sensorGrid: {
    flexDirection: 'row',
    flexWrap: 'wrap',
    justifyContent: 'space-between',
  },
  sensorCard: {
    width: '45%',
    backgroundColor: 'rgba(255, 255, 255, 0.4)',
    padding: 15,
    borderRadius: 10,
    marginBottom: 15,
    alignItems: 'center',
    borderWidth: 2,
    borderColor: 'transparent',
  },
  sensorAlerta: {
    backgroundColor: '#FFD1D1',
    borderColor: '#E73A4F',
  },
  sensorLabel: {
    fontSize: 12,
    color: '#1D2323',
    fontWeight: 'bold',
    textTransform: 'uppercase',
  },
  sensorValor: {
    fontSize: 24,
    color: '#1D2323',
    fontWeight: '900',
    marginTop: 5,
  },
  textoAlerta: {
    color: '#E73A4F',
  },
  painelBotoes: {
    width: '100%',
    paddingHorizontal: 10,
  },
  botaoReabastecer: {
    backgroundColor: '#F8DE59', // Amarelo direcional do BMO
    padding: 15,
    borderRadius: 30,
    alignItems: 'center',
    marginBottom: 30,
    borderWidth: 3,
    borderColor: '#1D2323',
  },
  textoBotao: {
    color: '#1D2323',
    fontWeight: '900',
    fontSize: 16,
  },
  tituloControles: {
    fontSize: 18,
    fontWeight: 'bold',
    color: '#1D2323',
    marginBottom: 15,
  },
  controleLinha: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    alignItems: 'center',
    backgroundColor: 'rgba(29, 35, 35, 0.1)',
    padding: 15,
    borderRadius: 10,
    marginBottom: 10,
  },
  controleLabel: {
    fontSize: 16,
    color: '#1D2323',
    fontWeight: 'bold',
  },
});