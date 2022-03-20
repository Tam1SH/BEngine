/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow strict-local
 */

import React from 'react';
import Node from 'react';
import {
	SafeAreaView,
	ScrollView,
	StatusBar,
	StyleSheet,
	Text,
	useColorScheme,
	View,
} from 'react-native';

import {
	Colors,
	DebugInstructions,
	Header,
	LearnMoreLinks,
	ReloadInstructions,
} from 'react-native/Libraries/NewAppScreen';

import { NativeModules } from 'react-native';
import { Alert } from 'react-native-windows';



const App = () => {
	const isDarkMode = useColorScheme() === 'dark';

	const backgroundStyle = {
	backgroundColor: isDarkMode ? Colors.darker : Colors.lighter,
	};

	return (
	<View>
		<Text>
		{ NativeModules.FancyMath.add(NativeModules.FancyMath.Pi + NativeModules.FancyMath.E, function (result : any) {
		Alert.alert(
			'FancyMath',
			`FancyMath says ${NativeModules.FancyMath.Pi} + ${NativeModules.FancyMath.E} = ${result}`,
			[{ text: 'OK' }],
			{cancelable: false});
		})}
		</Text>
    </View>
  );
};

const styles = StyleSheet.create({
  sectionContainer: {
    marginTop: 32,
    paddingHorizontal: 24,
  },
  sectionTitle: {
    fontSize: 24,
    fontWeight: '600',
  },
  sectionDescription: {
    marginTop: 8,
    fontSize: 18,
    fontWeight: '400',
  },
  highlight: {
    fontWeight: '700',
  },
});

export default App;
