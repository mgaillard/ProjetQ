import { Component, OnInit } from '@angular/core';

import { SearchResult } from '../shared/search-result'
import { SearchService } from '../shared/search.service'

@Component({
  selector: 'app-search-component',
  templateUrl: './search-component.component.html',
  styleUrls: ['./search-component.component.css'],
  providers: [SearchService]
})
export class SearchComponentComponent implements OnInit {
  query: string;
  results: SearchResult[] = null;

  constructor(private searchService: SearchService) { }

  ngOnInit() {
  }

  search(): void {
    this.searchService.searchKNearest(this.query)
      .then(results => this.results = results);
  }
}
