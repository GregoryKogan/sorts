// Utilities
import { defineStore } from 'pinia';

export const useAppStore = defineStore('app', {
  state: () => ({
    frameRate: 0 as number,
  }),
  actions: {
    setFrameRate(frameRate: number) {
      this.frameRate = frameRate;
    },
  },
});