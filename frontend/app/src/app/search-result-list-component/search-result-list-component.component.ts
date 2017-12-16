import { Component, OnInit, Input } from '@angular/core';

import { SearchResult } from '../shared/search-result'

@Component({
  selector: 'app-search-result-list-component',
  templateUrl: './search-result-list-component.component.html',
  styleUrls: ['./search-result-list-component.component.css']
})
export class SearchResultListComponentComponent implements OnInit {
  @Input() results: SearchResult[];

  constructor() { }

  ngOnInit() {
  }

}
