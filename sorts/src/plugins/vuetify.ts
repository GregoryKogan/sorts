/**
 * plugins/vuetify.ts
 *
 * Framework documentation: https://vuetifyjs.com`
 */

// Styles
import '@mdi/font/css/materialdesignicons.css';
import 'vuetify/styles';

// Composables
import { createVuetify } from 'vuetify';

// https://vuetifyjs.com/en/introduction/why-vuetify/#feature-guides
export default createVuetify({
  theme: {
    defaultTheme: "dark",
    themes: {
      dark: { // tokyo night storm theme
        dark: true,
        colors: {
          background: "#24283b",
          primary: "#7aa2f7",
          secondary: "#bb9af7",
          surface: "#414868",
          error: "#f7768e",
          info: "#7dcfff",
          success: "#9ece6a",
          warning: "#e0af68",
          "on-background": "#c0caf5",
          "on-surface": "#c0caf5",
        },
      },
    },
  },
});