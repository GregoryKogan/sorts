// Utilities
import { defineStore } from 'pinia';

export const useAppStore = defineStore('app', {
  state: () => ({
    frameRate: 0 as number,
    comparisons: 0 as number,
    swaps: 0 as number,
  }),
  actions: {
    setFrameRate(frameRate: number) {
      this.frameRate = frameRate;
    },
    setComparisons(comparisons: number) {
      this.comparisons = comparisons;
    },
    setSwaps(swaps: number) {
      this.swaps = swaps;
    },
  },
});