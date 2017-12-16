import { Injectable } from '@angular/core';
import { Http, RequestOptions, URLSearchParams } from '@angular/http';

import 'rxjs/add/operator/toPromise';

import { SearchResult } from './search-result';

@Injectable()
export class SearchService {
  private searchUrl = '/api/search';

  constructor(private http: Http) { }

  searchRadius(query: string): Promise<SearchResult[]> {
    let params = new URLSearchParams();
    params.set('url', query);
    params.set('method', 'radius');

    let request_options = new RequestOptions({params: params});

    return this.http.get(this.searchUrl, request_options)
             .toPromise()
             .then(response => response.json().results as SearchResult[])
             .catch(this.handleError);
  }

  searchKNearest(query: string): Promise<SearchResult[]> {
    let params = new URLSearchParams();
    params.set('url', query);
    params.set('method', 'knearest');

    let request_options = new RequestOptions({params: params});

    return this.http.get(this.searchUrl, request_options)
             .toPromise()
             .then(response => response.json().results as SearchResult[])
             .catch(this.handleError);
  }

  private handleError(error: any): Promise<any> {
    console.error('An error occurred', error);
    return Promise.reject(error.message || error);
  }
}
